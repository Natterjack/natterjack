require 'rake'
require 'rake/clean'
require 'rake/tasklib'

## Configuration
#
# Represents configuration for a single build output. E.g. a Debug or
# Release build of a library or a test executable.

class Configuration
  
  attr_reader :name

  # Flags to pass to the C++ compiler
  attr_accessor :cxx_flags
  
  # Compilation command
  attr_accessor :cxx

  # Source directories
  attr_accessor :src_dirs

  # Linker flags - just passed to the C++ Compiler
  attr_accessor :ld_flags

  # Run output
  attr_accessor :run_output

  def initialize(name)
    @name = name
    @cxx_flags = []
    @ld_flags = []
    @src_dirs = []
    @cxx = "clang++ -std=c++11"
    @run_output = false
  end

end

## Project
#
# Represents a single logical build item, such as a dynamic library or
# an executable. Contains one or more configurations.

class Project < Rake::TaskLib

  attr_accessor :name

  # The base directory for this project
  attr_accessor :base_dir
  
  def initialize(name)
    setup name
    if block_given?
      yield self
    else
      create_default_configuration
    end
    write_rules
  end

  ## Setup
  #
  # Intialise the default state of the project.
  
  def setup(name)
    @name = name
    @configurations = []
    @base_dir = name
  end

  ## Create Default Configuration
  #
  # Initialises a simple configuration if the project wasn't
  # configured with any.
  
  def create_default_configuration
    configuration 'release'
  end

  ## Configuration
  #
  # Creates and initialises a configuration and then attaches it to
  # the project.

  def configuration(config_name)
    config = Configuration.new config_name
    yield config if block_given?
    @configurations << config
  end

  ## Expand Path
  #
  # Expands a path relative to the project directory

  def expand_path(path)
    File.join base_dir, path
  end

  ## Source Files
  #
  # Finds all of the files with a given extension in the source
  # directory of a configuration

  def src_files(configuration, extension)
    Rake::FileList.new do |fl|
      configuration.src_dirs.each do |dir|
        fl.include "#{expand_path(dir)}/*.#{extension}"
      end
    end
  end

  ## Write Rules
  #
  # Turns the project into a set of rules for Rake to execute

  def write_rules

    configuration_names = []

    all_ragel_files = []

    @configurations.each do |configuration|

      # The directory where we will put the exe at the end of this
      bin_dir = "bin/#{name}/#{configuration.name}"
      directory bin_dir

      # Collect all of the c++ files we can find
      cxx_files = src_files configuration, "cpp"

      # Collect the ragel files
      ragel_files = src_files configuration, "ragel"
      cxx_files.include ragel_files.pathmap "%X.cpp"

      all_ragel_files.concat ragel_files

      cxx_files.uniq!

      # One-shot compile and link
      output_file = "#{bin_dir}/#{name}"
      file output_file => cxx_files do
        cflags = configuration.cxx_flags.join " "
        ldflags = configuration.ld_flags.join " "
        files = cxx_files.join " "
        sh %{#{configuration.cxx} #{cflags} #{ldflags} -o #{output_file} #{files}}
      end

      file output_file => bin_dir
      CLOBBER.include output_file

      configuration_name = "#{name}_#{configuration.name}".intern
      desc "Bulid #{output_file}."
      task configuration_name => output_file

      configuration_names << configuration_name

      if configuration.run_output
        run_target = "run_#{name}".intern

        task run_target => output_file do
          sh output_file
        end
      end
    end

    # for each ragel file convert it to a cpp file for compilation
    all_ragel_files.uniq.each do |rlfile|
      cxx_file = rlfile.pathmap "%X.cpp"

      CLEAN.include cxx_file

      file cxx_file => [rlfile] do
        sh %{ragel -o #{cxx_file} #{rlfile}}
      end
    end

    desc "Build #{name}"
    multitask name.intern => configuration_names
  end
end

# targets
Project.new 'natterjack' do |project|
  debug_cxx_flags = %w{-g -DDEBUG -o0}
  dirs = [ 'src' ]
  project.configuration 'debug' do |debug|
    debug.cxx_flags |= %w{-DNDEBUG -o3}
    debug.src_dirs.concat dirs
  end
  project.configuration 'release' do |release|
    release.cxx_flags |= debug_cxx_flags
    release.src_dirs.concat dirs
  end
  project.configuration 'test' do |test|
    test.cxx_flags |= debug_cxx_flags
    gtest_dir = ENV['GTEST_DIR']
    test.cxx_flags << "-I#{gtest_dir}/include"
    test.ld_flags << "#{gtest_dir}/lib/.libs/libgtest_main.a"
    test.ld_flags << "#{gtest_dir}/lib/.libs/libgtest.a"
    test.src_dirs.concat dirs
    test.src_dirs << 'test'
    test.run_output = true
  end
end

# Extra dependancy info (and pseudo tasks)
multitask :all => [:natterjack]

task :test => [:run_natterjack]

task :default => :all
