{
  description = "Embedded ARM dev shell with Python packages";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.11";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
	
	dependencies = [
          pkgs.cmake
          pkgs.gcc-arm-embedded-10
          pkgs.mcuboot-imgtool
          pkgs.gtkwave
          pkgs.jupyter
      	];

        # Python packages
      	pythonEnv = pkgs.python3.withPackages (py: [
          py.cbor
          py.cbor2
          py.click
          py.cryptography
          py.intelhex
          py.pyyaml
          py.jinja2
          py.ninja
          py.kconfiglib
          py.tkinter
          py.matplotlib
          py.pyserial
      	]);
 
      in {
        devShells.default = pkgs.mkShell {
          name = "tfm-dev-shell";

          buildInputs = [
            dependencies
            pythonEnv
          ];

          shellHook = ''
          echo "ARM dev environment ready."
	  
          # If fish exists, open it
          if command -v fish &> /dev/null; then
            exec fish
          fi
          '';
        };
      }
    );
}
