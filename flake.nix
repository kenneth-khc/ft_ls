{
  description = "ft_ls development shell";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
      ...
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells = with pkgs; {
          default = mkShell {
            packages = [
              clang
              clang-tools
              gnumake
              gdb
              bear
              bash
            ];
            hardeningDisable = [ "all" ];
          };
        };
      }
    );
}
