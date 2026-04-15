import ctypes
import os

class BloomFilter:
    def __init__(self, projected_elements, false_positive_rate, lib_path="./libbloomfilter.so"):
        if not os.path.exists(lib_path):
            raise FileNotFoundError(f"Shared library not found at {lib_path}. Please build the project first.")
        
        self.lib = ctypes.CDLL(lib_path)
        
        # Define function signatures
        self.lib.bloom_filter_new.argtypes = [ctypes.c_uint64, ctypes.c_double]
        self.lib.bloom_filter_new.restype = ctypes.c_void_p
        
        self.lib.bloom_filter_free.argtypes = [ctypes.c_void_p]
        
        self.lib.bloom_filter_add.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
        
        self.lib.bloom_filter_check.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_size_t]
        self.lib.bloom_filter_check.restype = ctypes.c_bool
        
        self.obj = self.lib.bloom_filter_new(projected_elements, false_positive_rate)

    def __del__(self):
        if hasattr(self, 'obj') and self.obj:
            self.lib.bloom_filter_free(self.obj)

    def add(self, data):
        if isinstance(data, str):
            data = data.encode('utf-8')
        self.lib.bloom_filter_add(self.obj, data, len(data))

    def __contains__(self, data):
        if isinstance(data, str):
            data = data.encode('utf-8')
        return self.lib.bloom_filter_check(self.obj, data, len(data))

if __name__ == "__main__":
    # Example usage (assumes libbloomfilter.so is in the current directory or build folder)
    # To run this, you might need: export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(pwd)/build
    try:
        # Check various common paths
        possible_paths = [
            "../../build/libbloomfilter.so",
            "./build/libbloomfilter.so",
            "./libbloomfilter.so"
        ]
        
        lib_path = None
        for path in possible_paths:
            if os.path.exists(path):
                lib_path = path
                break
                
        if lib_path is None:
            lib_path = "./libbloomfilter.so"
            
        bf = BloomFilter(1000, 0.01, lib_path=lib_path)
        bf.add("hello")
        bf.add("world")
        
        print(f"Contains 'hello': { 'hello' in bf }")
        print(f"Contains 'world': { 'world' in bf }")
        print(f"Contains 'python': { 'python' in bf }")
    except Exception as e:
        print(f"Error: {e}")
        print("Note: This script requires libbloomfilter.so to be built and accessible.")
