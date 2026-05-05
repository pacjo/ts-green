{ pkgs, lib, config, inputs, ... }:

{
    languages = {
        # PlatformIO
        cplusplus.enable = true;

        # Python server
        python = {
            enable = true;
            venv = {
                enable = true;
                requirements = ''
                    prometheus-client
                '';
            };
        };
    };

    packages = with pkgs; [
        # general
        git

        # sensor side
        platformio

        # server side
        grafana
    ];

    processes = {
        server.exec = "python3 ./server/main.py";

        grafana.exec = ''
            mkdir -p "$DEVENV_STATE/grafana/data" "$DEVENV_STATE/grafana/logs" "$DEVENV_STATE/grafana/plugins"

            GF_PATHS_DATA="$DEVENV_STATE/grafana/data" \
            GF_PATHS_LOGS="$DEVENV_STATE/grafana/logs" \
            GF_PATHS_PLUGINS="$DEVENV_STATE/grafana/plugins" \
            grafana server --homepath ${pkgs.grafana}/share/grafana
        '';
    };

    services.prometheus = {
        enable = true;
        port = 9080;

        scrapeConfigs = [
            {
                job_name = "python-middleware";
                scrape_interval = "1s";
                static_configs = [
                    {
                        targets = [ "localhost:8000" ];  # per python config
                    }
                ];
            }
        ];
    };

    containers."server" = {
        name = "scir-server";
        # exclude the `sensor/` codebase from the final image
        copyToRoot = lib.cleanSourceWith {
            src = ./.;
            filter = path: type: baseNameOf path != "sensor";
        };
    };

    # TODO: introduce main server task/process/service to start middleware script + prometheus/grafana part of stack

    env = {
        # TODO: use $PWD
        PLATFORMIO_CORE_DIR = ".platformio";
    };
}
