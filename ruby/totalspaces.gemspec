Gem::Specification.new do |s|
  s.name = %q{totalspaces}
  s.version = "0.3"

  s.authors = ["Stephen Sykes"]
  s.date = %q{2013-02-02}
  s.description = %q{This allows you to control the TotalSpaces desktop manager for mac from ruby.}
  s.email = %q{stephen@binaryage.com}
  s.files = [
    "README.rdoc",
    "MIT_LICENCE",
    "lib/totalspaces.rb",
    "lib/libtotalspacesapi.dylib",
    "lib/TSLib.h"
  ]
  s.homepage = %q{https://github.com/binaryage/totalspaces-api/tree/master/ruby}
  s.rdoc_options = ["--charset=UTF-8"]
  s.require_paths = ["lib"]
  s.summary = %q{TotalSpaces control from ruby}
  s.add_dependency('ffi', '>= 1.0.11')
end
