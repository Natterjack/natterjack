require 'rake'
require 'rake/clean'
require 'rake/tasklib'
require 'rake/testtask'

desc "Compile the cargo crates"
task :natterjack do
  sh %{cargo build}
end

desc "Run the rust tests"
task :natterjack_test do
  sh %{cargo test}
end

desc "Run the spec tests"
Rake::TestTask.new("test_spec") do |t|
  t.test_files = ['spec/test_spec.rb']
end
task :test_spec => [:natterjack]

docs_target = 'docs/_build/'
desc "Build the Sphinx Documentation"
task :docs => Rake::FileList['docs/**', 'README.rst'] do
  sh %{sphinx-build -b html docs/ #{docs_target}}
end
CLOBBER.include docs_target

desc "Build and serve the documentation"
task :docserve => :docs do
  sh %{(cd #{docs_target} && python -mSimpleHTTPServer)}
end

# Extra dependancy info (and pseudo tasks)
task :all => [:natterjack]

desc "Run **all** the tests"
task :test => [:natterjack_test, :test_spec]

task :default => :all
