{ pkgs, lib, config, inputs, ... }:

{
    languages = {
        # PlatformIO
        cplusplus.enable = true;

        # Python server
        python = {
            enable = true;
            venv.enable = true;
            requirements = ''
                prometheus-client
            '';
        };
    };

    packages = with pkgs; [
        git
        platformio
    ];

    env = {
        # TODO: use $PWD
        PLATFORMIO_CORE_DIR = "./sensor/.platformio";
    };
}
