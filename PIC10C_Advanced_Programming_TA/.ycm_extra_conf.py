def FlagsForFile( filename, **kwargs ):
      return {
                  'flags': [ '-x', 'c++', '-Werror', 'std=c++14' ],
                    }
