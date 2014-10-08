require 'rake'
require 'rake/clean'
require 'rake/tasklib'

module Natterjack
  # Configuration stuff
  BIN_DIR = 'bin'
  BUILD_DIR = 'build'

  ## Executable
  # 
  # Represents the tasks required to build a native executable
  # from C++ code
  class Executable < Rake::TaskLib

    attr_accessor :name

    def initialize(name)
      @name = name
      yield self if block_given?
      _write_rules
    end

    def _write_rules
      # Get the file that we need to build
      exe_file = File.join(BIN_DIR, @name)
      ragel_files = Rake::FileList["#{@name}/*.ragel"]
      cxx_files = Rake::FileList["#{@name}/*.cpp"]

      converted_ragel_files = ragel_files.ext(".cpp")
      cxx_files |= converted_ragel_files

      obj_files = cxx_files.pathmap("#{BUILD_DIR}/%X.o")

      # Compile C++ to objects
      cxx_files.each do |cxx_file|
        object_file = cxx_file.pathmap("#{BUILD_DIR}/%X.o")
        CLEAN << object_file
        obj_dir = object_file.pathmap("%d")
        directory obj_dir
        file object_file => [cxx_file, obj_dir] do
          sh %{clang++ -std=c++11 -c -o #{object_file} #{cxx_file}}
        end
      end

      # convert ragel files to C++ code with ragel
      rule ".cpp" => ".ragel" do |t|
        sh "ragel -o #{t.name} #{t.source}"
      end

      # compile and link the executable
      file exe_file => obj_files do
        sh %{clang++ -std=c++11 -o #{exe_file} #{obj_files.join(" ")}}
      end

      # make sure we have a directory to compile into
      directory BIN_DIR
      task exe_file => BIN_DIR

      # create the test task
      test_name = "test_#{@name}"
      task test_name => exe_file do
        sh exe_file
      end

      # Create the wrapper task
      task @name.intern => exe_file

      CLEAN.include(converted_ragel_files)
      CLOBBER.include(exe_file)
    end

  end
  
end

# targets
Natterjack::Executable.new 'natterjack'

# Extra dependancy info (and pseudo tasks)
multitask :all => [:natterjack]

task :test => [ 'test_natterjack' ]

task :default => :all
