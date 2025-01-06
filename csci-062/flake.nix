{
  inputs = {
    utils.url = github:numtide/flake-utils;
    nixpkgs.url = github:NixOS/nixpkgs/nixos-23.11;
  };

  outputs = {
    self,
    nixpkgs,
    utils,
  }:
    utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {
      devShells = rec {
        # default = tbonet;
        tbonet = pkgs.mkShell {
          buildInputs = with pkgs; [
            # pyright
            (python3.withPackages (ps:
              with ps; [
                ipython
                jupyter
                notebook

                numpy
                pandas

                matplotlib
                scikit-learn
              ]))
          ];
          # shellHook = "jupyter notebook";
        };
      };
        packages.qnetwork = pkgs.stdenv.mkDerivation {
          pname = "social";
          version = "0.1.0";

          src = ./.;

          nativeBuildInputs = with pkgs; [ qt6.qmake qt6.wrapQtAppsHook ];
          buildInputs = [ ];

          installPhase = ''
            mkdir -p $out/bin
            cp socialnetwork $out/bin/social
          '';
        };
    });
}
