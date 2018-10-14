GBENCHMARK_DIR := benchmark
GBENCHMARK_HEADERS := $(wildcard $(GBENCHMARK_DIR)/src/*.h)
GBENCHMARK_SRCS := $(wildcard $(GBENCHMARK_DIR)/src/*.cc)
LIBGBENCHMARK := $(GBENCHMARK_DIR)/build/src/libbenchmark.a

BENCH_SOURCES := $(wildcard bench/*.cc)
BENCH_DFILES := $(BENCH_SOURCES:.cc=.d)
BENCH_OBJECTS := $(BENCH_SOURCES:.cc=.o)
BENCH_HEADERS := $(wildcard bench/*.h)  $(GBENCHMARK_HEADERS)
BENCH_INCLUDE := -I bench -I $(GBENCHMARK_DIR)/include
BENCHRUNNER := bench/run

.PHONY: benchmark
benchmark: $(BENCHRUNNER)
	@LD_LIBRARY_PATH=. $<


bench/%.o: bench/%.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(BENCH_INCLUDE) -c $< -o $@


$(LIBGBENCHMARK): $(GBENCHMARK_SRCS) $(GBENCHMARK_HEADERS)
	cd $(GBENCHMARK_DIR) && mkdir -p build
	cd $(GBENCHMARK_DIR)/build && cmake .. \
		-DCMAKE_BUILD_TYPE=RELEASE \
		-DBENCHMARK_ENABLE_GTEST_TESTS=OFF
	make -C $(GBENCHMARK_DIR)/build


$(BENCHRUNNER): $(LIBGBENCHMARK) $(BENCH_OBJECTS)
	$(CXX) -o $@ $(BENCH_OBJECTS) $(BENCH_LDFLAGS) $(BENCH_INCLUDE) \
		$(LIBGBENCHMARK) -lpthread -L. $(LDFLAGS)
