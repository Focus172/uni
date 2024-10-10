# CSEN - 20 Lab
The lab requires using the provided build system. However, for testing purposes
I have made my own. It can be ran and tested with:
```bash
zig build native-NUM
zig build test-NUM
```
where num is the number lab it is.

if you want to use the old build system then do:
```bash
rm env/src/*
cp src/LabNUMb-* env/src
cd env
make
```
