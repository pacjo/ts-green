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
        tio
        platformio

        # server side
        grafana
        ustreamer
    ];

    processes = {
        server.exec = "python3 ./server/main.py";

        grafana.exec = ''
            mkdir -p "$DEVENV_STATE/grafana/data" "$DEVENV_STATE/grafana/logs" "$DEVENV_STATE/grafana/plugins"

            # required setup
            export GF_PATHS_DATA="$DEVENV_STATE/grafana/data"
            export GF_PATHS_LOGS="$DEVENV_STATE/grafana/logs"
            export GF_PATHS_PLUGINS="$DEVENV_STATE/grafana/plugins"

            grafana server --homepath ${pkgs.grafana}/share/grafana
        '';

        ustreamer.exec = "ustreamer --device /dev/video0 --host 0.0.0.0 --port 8081";
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
