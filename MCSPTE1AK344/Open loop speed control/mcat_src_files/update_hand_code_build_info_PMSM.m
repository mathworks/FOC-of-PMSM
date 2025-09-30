% Copyright 2020-2024 NXP
%
% SPDX-License-Identifier: BSD-3-Clause
% The BSD-3-Clause license can be found at 
% https://spdx.org/licenses/BSD-3-Clause.html

function [ ] = update_hand_code_build_info_PMSM( )

% "coder.extrinsic(...)" lets unsupported functions be used *by* MATLAB
% Coder, provided that they aren't used *in* the generated code (They are
% unsupported, after all). Since these functions are all used to set up the
% compilation and makefile, they aren't actually used *in* the generated
% code.
coder.extrinsic( 'fileparts' );

% "mfilename( 'fullpath' )" returns the full name of the
% currently-executing file.
thisFilesFullName = mfilename( 'fullpath' );

% "fileparts(...)" returns the path part of a fully-qualified file name.
% Additionally, "coder.const(...)" is sometimes necessary to mark a
% variable as constant, which is sometimes required for some functions'
% arguments.
thisFilesAbsolutePath = coder.const( fileparts( thisFilesFullName ) );

% This adds the path to the header file as a "-I" argument to the build
% command, so the "#include" directive can be resolved during compilation.
coder.updateBuildInfo( 'addIncludePaths', thisFilesAbsolutePath );
coder.updateBuildInfo( 'addIncludePaths', [thisFilesAbsolutePath '\tpp'] );
coder.updateBuildInfo( 'addIncludePaths', [thisFilesAbsolutePath '\aml'] );

% This clarifies the path to the source file so that it can be found when
% the makefile runs.
coder.updateBuildInfo( 'addSourcePaths', thisFilesAbsolutePath );
coder.updateBuildInfo( 'addSourcePaths', [thisFilesAbsolutePath '\tpp'] );
coder.updateBuildInfo( 'addSourcePaths', [thisFilesAbsolutePath '\aml'] );

return;

end