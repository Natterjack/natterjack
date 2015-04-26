require 'test/unit'

NAT_EXE = '../target/debug/natterjack'

def methodname(natfile)
  ("test_"+natfile.gsub('/', '_').split('.')[0]).intern
end

class NatterjackSpec < Test::Unit::TestCase
  Dir.chdir File.expand_path('../', __FILE__)
  Dir.glob("**.nat").each do |natfile|
    define_method methodname(natfile) do
      output = `#{NAT_EXE} #{natfile}`
      assert 0 == $?, "Expected successful exit"
    end
  end
end
