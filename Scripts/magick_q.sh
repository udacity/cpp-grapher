#!/bin/sh

set -e
shopt -s extglob

EXISTS=$(which convert)

if [ -z "$EXISTS" ]; then
  # ImageMagic appears to be missing
  exit 1
fi

FULL_IMAGEMAGICK_VERSION_OUTPUT=$(convert --version)

# grabs the Q number of ImageMagick's installation
re="^Version\: ImageMagick 7\.[0-9]+.+ Q([0-9]+)"
[[ $FULL_IMAGEMAGICK_VERSION_OUTPUT =~ $re ]]
Q_NUMBER=${BASH_REMATCH[1]}

# prints the Q number (without endl) for cmake to pick up later
printf $Q_NUMBER
