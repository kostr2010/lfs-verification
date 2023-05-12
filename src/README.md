# DESCRIPTION

# SUBMODULES

```
git submodule update --init --recursive
```

# BUILD

```
mdir build
cd $_
cmake .. && make
```

# RUN

to run tests, execute

```
./build/tests/gtests
```

this will run test suite and dump `trace.log` to `build` folder, that can then be passed to `verify_trace.sh` script
