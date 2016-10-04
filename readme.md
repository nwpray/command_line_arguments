# Portsetter Readme

## Layout

* 1.0 - Initial Project
* 1.1 - Change Order 1
* 1.2 - Change Order 2
* 1.3 - Change Order 3

## Installation

For installation, run
`./install.sh`
in the terminal from within the latest versions directory.
As of this documents last update it will be 1.3

If you get the response, 
`bash: ./install.sh: Permission denied`
then run
`chmod 755 install.sh`
from the terminal and attempt install again.

## Usage

To get a detailed usage list, run
`setport -h`
from terminal.

## Testing

To run test to ensure that the program is still working, run
`setporttest`
in the terminal after installation

## Uninstall

To uninstall the program and its aliases, run
`./uninstall.sh`
from the terminal from the same directory you ran the install script from
As of this document, the latest version is 1.3

If you get the response
`./uninstall.sh`
then run
`chmod 755 uninstall.sh`
and run uninstall againse

### Install and Uninstall scripts will automatically restart your bash session on completion.
### If you do not have a language defined the program will default to english. In this case all output tests will fail to do to the no language defined message being included.