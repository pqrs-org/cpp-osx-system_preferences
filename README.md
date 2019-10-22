[![Build Status](https://github.com/pqrs-org/cpp-osx-system_preferences/workflows/CI/badge.svg)](https://github.com/pqrs-org/cpp-osx-system_preferences/actions)
[![License](https://img.shields.io/badge/license-Boost%20Software%20License-blue.svg)](https://github.com/pqrs-org/cpp-osx-system_preferences/blob/master/LICENSE.md)

# cpp-osx-system_preferences

A utility for `CFPreferences`.

## Requirements

cpp-osx-system_preferences depends the following classes.

- [pqrs::cf::number](https://github.com/pqrs-org/cpp-cf-number)
- [pqrs::cf::string](https://github.com/pqrs-org/cpp-cf-string)
- [pqrs::hash](https://github.com/pqrs-org/cpp-hash)
- [pqrs::osx::iokit_types](https://github.com/pqrs-org/cpp-osx-iokit_types)

## Install

### Using package manager

You can install `include/pqrs` by using [cget](https://github.com/pfultz2/cget).

```shell
cget install pqrs-org/cget-recipes
cget install pqrs-org/cpp-osx-system_preferences
```

### Manual install

Copy `include/pqrs` directory into your include directory.
