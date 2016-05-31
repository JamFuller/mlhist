# mlhist [![Build Status](https://travis-ci.org/JamFuller/mlhist.svg?branch=develop)](https://travis-ci.org/JamFuller/mlhist)

MarkLogic history metrics.

## quickstart

1. Download latest [release](https://github.com/JamFuller/mlhist/releases)

2. create ~.mlhist 

```
touch ~/.mlhist
```

provide MarkLogic connection details

```
host=localhost
protocol=http
user=admin
pass=admin
```

3. run mlhist 

```
mlhist
```

## usage

## build, test, & install

Using either [develop](https://github.com/JamFuller/mlhist/tree/develop) or [master](https://github.com/JamFuller/mlhist/tree/master) branch

```
cmake && make && make test

```
to install 

```
make install

```
