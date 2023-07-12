$dataPath = $PsScriptRoot + "..\data\"

# Max length of a path part is 8
$maxPathPartViolations = ls $dataPath\games -Recurse | % Name | where Length -gt 8
if( $maxPathPartViolations )
{
    Write-Error "The following path parts are too long, they need to be max 8 chars to satisfy BUFFER_PATH_MAX_LENGTH: $maxPathPartViolations"
}
