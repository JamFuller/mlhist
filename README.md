# mlhist [![Build Status](https://travis-ci.org/JamFuller/mlhist.svg?branch=develop)](https://travis-ci.org/JamFuller/mlhist)

Generate graphs and integrate data with commandline interface to MarkLogic history metrics.

## For the impatient

To get quickly started:

1. Download latest [release](https://github.com/JamFuller/mlhist/releases) or [build yourself](https://github.com/JamFuller/mlhist#Build-test--install).

2. Create ~/.mlhist 

```
touch ~/.mlhist
```

3. edit ~/.mlhist, supplying your MarkLogic environment connection details

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

5. learn more by viewing [examples](https://github.com/JamFuller/mlhist#examples)


## Examples

get help 
```
mlhist -h
```

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

Find metrics
```
mlhist 
```

## Build, test, & install

To build you will need to ensure [cmake v3.2.2](https://cmake.org/) or above is installed (I know, I know ... times do change).

Using either [develop](https://github.com/JamFuller/mlhist/tree/develop) or [master](https://github.com/JamFuller/mlhist/tree/master) branch

```
cmake && make && make test

```

All tests should pass and mlhist/mlhist binary should have been built.

To install: 

```
make install

```

## Issues, feature requests & PR's

[File bug reports](https://github.com/jamfuller/mlhist/labels/Bug), [feature requests](https://github.com/jamfuller/mlhist/labels/enhancement), and [pull requests](https://github.com/jamfuller/mlhist/pulls) through GitHub. 

### License

[Apache License v2.0](LICENSE)