#!/bin/bash

make test_mixer && make test_sigpath && make test_engine && make test_voice && \
./dst/test_mixer && \
./dst/test_sigpath && \
./dst/test_voice && \
./dst/test_engine