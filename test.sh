#!/bin/bash

make test_mixer && make test_voice && make test_engine && make test_voice && \
./dst/test_mixer && \
./dst/test_voice && \
./dst/test_voice && \
./dst/test_engine