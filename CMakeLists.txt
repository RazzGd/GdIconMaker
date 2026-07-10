name: Build Geode Mod

on:
  workflow_dispatch:

env:
  ACTIONS_ALLOW_USE_UNSECURE_NODE_VERSION: true

jobs:
  build:
    strategy:
      fail-fast: false
      matrix:
        config:
          - name: Android64
            os: ubuntu-latest
            target: Android64

    name: ${{ matrix.config.name }}
    runs-on: ${{ matrix.config.os }}

    steps:
      - name: Checkout Code
        uses: actions/checkout@v4

      # FIX: Installs the actual Geode SDK binaries directly onto the machine!
      - name: Build the mod
        uses: geode-sdk/build-geode-mod@main
        with:
          target: ${{ matrix.config.target }}
          sdk: latest
          cli: latest
          combine: true

  package:
    name: Package builds
    runs-on: ubuntu-latest
    needs: ['build']

    steps:
      - uses: geode-sdk/build-geode-mod/combine@main
        id: build

      - uses: actions/upload-artifact@v4
        with:
          name: Build Output
          path: ${{ steps.build.outputs.build-output }}
