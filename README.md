# mlhist [![Build Status](https://travis-ci.org/JamFuller/mlhist.svg?branch=develop)](https://travis-ci.org/JamFuller/mlhist)

MarkLogic history metrics.

## quickstart

To start using mlhist quickly:

1. Download latest [release](https://github.com/JamFuller/mlhist/releases)

2. Create ~.mlhist 

```
touch ~/.mlhist
```

3. in ~/.mlhist, supply MarkLogic connection details

```
host=localhost
protocol=http
user=admin
pass=admin
```

4. run mlhist 

```
mlhist
```

## usage

To get all options for running mlhist 

```
mlhist -h
```

mlhist resources/resource [options] - get MarkLogic history metrics
    -f    : format (xml|json)
    -p    : period (raw|hour|day)
    -s    : start date (ex. 2015-03-21T17:38:00)
    -e    : end date (ex. 2015-03-22T17:58:00)
    -m    : meter(s) (resource specific)
    -r    : resource (databases|forests|servers|hosts)
    -o    : output (graph)
    -g    : gnuplot script
    -v    : verbose (show http call)
    -q    : quiet (suppress banner)

## examples

Get all metrics
```
mlhist
```

Get all metrics data
```
mlhist
```

Get all forest metrics
```
mlhist forests
```

Get all metrics for range of time
```
mlhist
```

Get all metrics for a range of time with different period
```
mlhist
```

Get specific metric
```
mlhist
```

list metrics
```
```


## build, test, & install

You will need [cmake v3.2.2](https://cmake.org/) or above (I know, I know ... times change).

Using either [develop](https://github.com/JamFuller/mlhist/tree/develop) or [master](https://github.com/JamFuller/mlhist/tree/master) branch

```
cmake && make && make test

```

all tests should pass and mlhist/mlhist binary should be built.

To install 

```
make install

```
