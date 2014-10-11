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

  def initialize(name)
    @name = name
    @cxx_flags = []
    @src_dirs = []
    @cxx = "clang++ -std=c++11"
  end

end

## Project
#
# Represents a single logical build item, such as a dynamic library or
# an executable. Contains one or more configurations.

class Project < Rake::TaskLib

  attr_accessor :name
  
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

  ## Write Rules
  #
  # Turns the project into a set of rules for Rake to execute

  def write_rules

    configuration_names = []

    @configurations.each do |configuration|

      # The directory where we will put the exe at the end of this
      bin_dir = "bin/#{name}/#{configuration.name}"
      directory bin_dir

      cxx_files = Rake::FileList["#{name}/*.cpp"]

      ragel_files = Rake::FileList["#{name}/*.ragel"]
      ragel_files.each do |rlfile|
        cxx_file = rlfile.pathmap "%X.cpp"

        cxx_files << cxx_file
        CLEAN.include cxx_file

        file cxx_file => rlfile do
          sh %{ragel -o #{cxx_file} #{rlfile}}
        end
      end

      # One-shot compile and link
      output_file = "#{bin_dir}/#{name}"
      file output_file => cxx_files do
        sh %{#{configuration.cxx} #{configuration.cxx_flags.join " "} -o #{output_file} #{cxx_files.join " "}}
      end
      file output_file => bin_dir
      CLOBBER.include output_file

      configuration_name = "#{name}-#{configuration.name}".intern
      desc "Bulid #{output_file}."
      task configuration_name => output_file
      configuration_names << configuration_name
    end

    desc "Build #{name}"
    multitask name.intern => configuration_names
  end
end

# targets
Project.new 'natterjack' do |project|
  project.configuration 'debug' do |debug|
    debug.cxx_flags |= %w{-g -DDEBUG -o0}
    debug.src_dirs << '.'
  end
  project.configuration 'release' do |release|
    release.cxx_flags |= %w{-DNDEBUG -o3}
    release.src_dirs << '.'
  end
end

# Extra dependancy info (and pseudo tasks)
multitask :all => [:natterjack]

task :default => :all
