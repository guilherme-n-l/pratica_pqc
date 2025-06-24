{
  description = "C++ dev env with clang++ and liboqs";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
        };
      in
      {
        devShells.default = pkgs.mkShell {
          name = "cpp-liboqs-env";

          nativeBuildInputs = with pkgs; [
            clang
            cmake
            liboqs
            python310
            python310Packages.paho-mqtt
            python310Packages.cryptography
            mosquitto
          ];

          shellHook = ''
            export CXX=clang++
            export LIBOQS_LIB_DIR=${pkgs.liboqs}/lib
            export LIBOQS_INCLUDE_DIR=${pkgs.liboqs.dev}/include
            export LD_LIBRARY_PATH=$LIBOQS_LIB_DIR:$LD_LIBRARY_PATH
            export CPLUS_INCLUDE_PATH=$LIBOQS_INCLUDE_DIR:$CPLUS_INCLUDE_PATH
            cat > .clangd <<EOF
            CompileFlags:
              Add: [
                "-I$LIBOQS_INCLUDE_DIR",
                "-std=c++17"
              ]
            EOF

            echo "clang++ and liboqs are ready to use"
          '';
        };
      });
}

