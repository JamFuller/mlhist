# mlhist [![Build Status](https://travis-ci.org/JamFuller/mlhist.svg?branch=develop)](https://travis-ci.org/JamFuller/mlhist)

MarkLogic history metrics.

## quickstart

1. Download latest https://github.com/JamFuller/mlhist/releases#release

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

Using either https://github.com/JamFuller/mlhist/tree/develop#develop or https://github.com/JamFuller/mlhist/tree/master#master branch

```
cmake && make && make test

```
to install 

```
make install

```
