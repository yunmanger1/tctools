#!/bin/bash

# Clear file from unused "defines" and comments and copy it to the clipboard

clear < $1 >clear.$1
tcp clear.$1
rm clear.$1
