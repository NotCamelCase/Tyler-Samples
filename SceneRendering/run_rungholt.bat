@echo off

echo "RUNNING"
echo "This may take a while..."
call SceneRendering.exe -obj_name assets\rungholt.obj -run_benchmark -num_frames 200 > rungholt_log.txt

echo "DONE!"

pause