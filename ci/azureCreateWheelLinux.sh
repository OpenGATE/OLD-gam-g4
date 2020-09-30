#!/bin/bash

set -e -x
echo ${PYTHONFOLDER}
#git clone --recurse-submodules https://github.com/tbaudier/gam_g4.git gam_g4
cd /home/gam_g4
git checkout pipInstall
#git pull --recurse-submodules
export PATH=/software/cmake/cmake-3.18.2-Linux-x86_64/bin/:${PATH}
source /software/geant4/bin/geant4make.sh
export CMAKE_PREFIX_PATH=/software/geant4/bin:/software/itk/bin/:${CMAKE_PREFIX_PATH}
/opt/python/${PYTHONFOLDER}/bin/python setup.py sdist bdist_wheel
auditwheel repair /home/gam_g4/dist/*.whl -w /software/wheelhouse/ --plat "manylinux2014_x86_64"
cp -r /software/wheelhouse /home/
#/opt/python/${PYTHONFOLDER}/bin/pip install twine
#/opt/python/${PYTHONFOLDER}/bin/twine upload --repository-url https://test.pypi.org/legacy/ wheelhouse/*manylinux2014*.whl

