# Sunflower

Sunflower is a cross-platform screen time management application that tracks time spent in selected applications and minimizes them when their configured time allowance is exceeded.

## Build

Clone the repository:

```bash
git clone https://github.com/bergamontt/sunflower.git
cd sunflower
```

Configure and build the project:

```bash
cmake -S . -B build
cmake --build build
```

## Run

Run the application:

```bash
./build/src/app/sunflower
```

Run the test executable directly:

```bash
./build/tests/tests
```

Alternatively, build and run the application in one command:

```bash
cmake --build build --target run
```

Build and run the tests:

```bash
cmake --build build --target test
```

