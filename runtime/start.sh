export LD_LIBRARY_PATH=$(pwd):${LD_LIBRARY_PATH}
nohup ./ctpdemo > out.log 2>&1 &
