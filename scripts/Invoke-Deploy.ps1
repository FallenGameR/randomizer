function dp
{
    C:\Users\alexk\.platformio\penv\Scripts\platformio.exe run
    if( $LASTEXITCODE -ne 0 ) { exit $LASTEXITCODE }
    C:\Users\alexk\.platformio\penv\Scripts\platformio.exe run --target upload --target monitor
}
