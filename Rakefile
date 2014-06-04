require 'rake'
require 'rake/clean'

# Configuration stuff
BIN_DIR = 'bin'
BUILD_DIR = 'build'

# Accumulators for build outputs
ALL_EXES = []
ALL_TEST = []

directory BIN_DIR

# Compilation commands
def build_exe name
  # Get the file that we need to build
  exe_file = File.join(BIN_DIR, name)
  cxx_files = Dir["#{name}/*.cpp"]
  file exe_file => cxx_files do
    sh %{clang++ -std=c++11 -o #{exe_file} #{cxx_files.join}}
  end
  task exe_file => BIN_DIR
  ALL_EXES << exe_file

  test_name = "test_#{name}"
  task test_name => exe_file do
    sh exe_file
  end

  ALL_TEST << test_name
end

# targets
build_exe 'natterjack'

CLOBBER << ALL_EXES

# Extra dependancy info (and pseudo tasks)
multitask :all => ALL_EXES

task :test => ALL_TEST

task :default => :all
