{
  "targets": [
#     {
#       "target_name": "greaseLog",

# ## required: build gperftools. Note the --enable-frame-pointers is needed on x86_64 systems
# ##  ./configure --prefix=`pwd`/../build --enable-frame-pointers
# ##
# ## from their README
# ## NOTE: When compiling with programs with gcc, that you plan to link
# ## with libtcmalloc, it's safest to pass in the flags
# ##
# ## -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free

#       "conditions": [
#         [
#           "OS=='mac'", {
#             "xcode_settings": {
#               "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
#               "WARNING_CFLAGS": [
#                 "-Wno-unused-variable",
#               ],
#             }
#           }
#         ],

#         [
#           "OS=='linux'", {
#           "doit" : '<!(deps/install_deps.sh)',

#       "sources": [
#         "logger.cc",
#         "grease.cc",
#         "local_strdup.c",
#         "error-common.cc",
#         "grease_client.c",
#         "client_logger.cc",
#         "deps/twlib/tw_alloc.cpp",
#         "deps/twlib/tw_utils.cpp"
#       ],
#       "ldflags" : [
#       ],
#       "include_dirs": [
#          "deps/twlib/include",
#          "deps/build/include",
#        	 "node_modules/nan",
#          "<!(node -e \"require('nan')\")"    # note, this is needed b/c with 'npm install' it places 'nan' in a different location - this may break in Yocto bb recipe
#       ],
#       'link_settings': {
#             'libraries': [
#                 '-ldl'
#             ]
#       },


#     'configurations': {
#       'Debug': {
#         'defines': [ 'ERRCMN_DEBUG_BUILD', 'LOGGER_HEAVY_DEBUG', 'GREASE_DEBUG_MODE' ], # , 'LOGGER_HEAVY_DEBUG'
#         "cflags": [
#           "-Wall",
#           "-std=c++11",
#           "-D_POSIX_C_SOURCE=200809L",
#           "-D_GNU_SOURCE",
#           "-DERRCMN_DEBUG_BUILD=1",
# #          "-DLOGGER_HEAVY_DEBUG=1",
#           "-fno-omit-frame-pointer",  # required by tcmalloc, but not a default on x86_64
# ## not needed since we explicitly call tcmalloc
# ##          "-fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free"
#           ],  
#           "ldflags" : [
#             "-L../deps/build/lib",
#             ## education: http://stackoverflow.com/questions/14889941/link-a-static-library-to-a-shared-one-during-build
#             "-Wl,-whole-archive ../deps/build/lib/libtcmalloc.a -Wl,-no-whole-archive" 
#           ]
# ##        'conditions': [
# ##          ['target_arch=="x64"', {
# ##            'msvs_configuration_platform': 'x64',
# ##          }],
# ##        ]
#       },
#       'Release': {
#         "cflags": [
#           "-Wall",
#           "-std=c++11",
#           "-D_POSIX_C_SOURCE=200809L",
#           "-D_GNU_SOURCE",
#           "-fno-omit-frame-pointer",  # required by tcmalloc, but not a default on x86_64
# ## not needed since we explicitly call tcmalloc
# ##          "-fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free"
#           ],  
#           "ldflags" : [
#             "-L../deps/build/lib",
#             "-Wl,-whole-archive ../deps/build/lib/libtcmalloc.a -Wl,-no-whole-archive" 
#           ]
#       }

#     },



#           }
#         ],  # end Linux




#       ]
#     }

    {
      "target_name": "grease_echo",
      "type": "executable",
      'conditions': [ 
        [ "OS =='linux'", {
      "sources": [ "grease_echo.c", "grease_client.c" ],
      'link_settings': {
            'libraries': [
                '-ldl'
            ]
      },
      'configurations': {
        'Debug': {
          "ldflags" : ["-ldl"],
          "cflags" : ["-ldl","-DGLOG_DEFAULT_TAG=GREASE_TAG_ECHO","-DGREASE_NO_LOCAL_SYMBOLS=1"]
        },
        'Release': {
          "ldflags" : ["-ldl"],
          "cflags" : ["-ldl","-DGLOG_DEFAULT_TAG=GREASE_TAG_ECHO","-DGREASE_NO_LOCAL_SYMBOLS=1"]        
          }
      }
      }  ] ]

    },



        {
      "target_name": "greaseLogClient",

## required: build gperftools. Note the --enable-frame-pointers is needed on x86_64 systems
##  ./configure --prefix=`pwd`/../build --enable-frame-pointers
##
## from their README
## NOTE: When compiling with programs with gcc, that you plan to link
## with libtcmalloc, it's safest to pass in the flags
##
## -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free

      "conditions": [
        [
          "OS=='mac'", {
            "xcode_settings": {
              "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
              "WARNING_CFLAGS": [
                "-Wno-unused-variable",
              ],
            }
          }
        ],

        [
          "OS=='linux'", {
          "doit" : '<!(deps/install_deps.sh)',

      "sources": [
        "grease_clientonly.cc",
        "local_strdup.c",
        "error-common.cc",
        "grease_client.c",
        "client_logger.cc",
#        "deps/twlib/tw_alloc.cpp",
#        "deps/twlib/tw_utils.cpp"
      ],
      "ldflags" : [
      ],
      "include_dirs": [
         "deps/twlib/include",
         "deps/build/include",
	       "node_modules/nan",
         "<!(node -e \"require('nan')\")"    # note, this is needed b/c with 'npm install' it places 'nan' in a different location - this may break in Yocto bb recipe
      ],
      'link_settings': {
            'libraries': [
                '-ldl'
            ]
      },


    'configurations': {
      'Debug': {
        'defines': [ 'ERRCMN_DEBUG_BUILD', 'LOGGER_HEAVY_DEBUG', 'GREASE_DEBUG_MODE' ], # , 'LOGGER_HEAVY_DEBUG'
        "cflags": [
          "-Wall",
          "-std=c++11",
          "-D_POSIX_C_SOURCE=200809L",
          "-D_GNU_SOURCE",
          "-DGREASE_NO_LOCAL_SYMBOLS=1",
          "-DERRCMN_DEBUG_BUILD=1",
#          "-DLOGGER_HEAVY_DEBUG=1",
          "-fno-omit-frame-pointer",  # required by tcmalloc, but not a default on x86_64
## not needed since we explicitly call tcmalloc
##          "-fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free"
          ],  
          "ldflags" : [
            "-L../deps/build/lib",
            ## education: http://stackoverflow.com/questions/14889941/link-a-static-library-to-a-shared-one-during-build
#            "-Wl,-whole-archive ../deps/build/lib/libtcmalloc.a -Wl,-no-whole-archive" 
          ]
##        'conditions': [
##          ['target_arch=="x64"', {
##            'msvs_configuration_platform': 'x64',
##          }],
##        ]
      },
      'Release': {
        "cflags": [
          "-Wall",
          "-std=c++11",
          "-D_POSIX_C_SOURCE=200809L",
          "-D_GNU_SOURCE",
          "-DGREASE_NO_LOCAL_SYMBOLS=1",
          "-fno-omit-frame-pointer",  # required by tcmalloc, but not a default on x86_64
## not needed since we explicitly call tcmalloc
##          "-fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free"
          ],  
          "ldflags" : [
            "-L../deps/build/lib",
#            "-Wl,-whole-archive ../deps/build/lib/libtcmalloc.a -Wl,-no-whole-archive" 
          ]
      }

    },



          }
        ],  # end Linux




      ]
    }







  ],
}
