{ pkgs, lib, config, inputs, ... }:

{
  languages.cplusplus.enable = true;

  packages = with pkgs; [
    git
    platformio
  ];

  env = {
    # TODO: use $PWD
    PLATFORMIO_CORE_DIR = "./.platformio";
  };
}
