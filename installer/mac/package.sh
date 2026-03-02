#!/bin/bash

pkgbuild --root "$1" --identifier com.noahh-sdk.noahh --scripts "installer/mac/Scripts" --install-location "/tmp/noahh-install" $2

