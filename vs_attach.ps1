param (
    [string]$ProcessName
)

# Load the Visual Studio DTE COM object
function Get-VisualStudio-DTE {
    $dteList = @()
    $rot = [System.Runtime.InteropServices.Marshal]::GetActiveObject("VisualStudio.DTE.17.0")  # for VS 2022
    if ($rot) { $dteList += $rot }
    return $dteList
}

# Find the process to attach to by name
$process = Get-Process -Name $ProcessName -ErrorAction SilentlyContinue | Select-Object -First 1

if ($process -eq $null) {
    Write-Output "Process $ProcessName not found."
    exit 1
}

# Get the Visual Studio DTE object
$dteInstances = Get-VisualStudio-DTE
if ($dteInstances.Count -eq 0) {
    Write-Output "No running Visual Studio instance found."
    exit 1
}

foreach ($dte in $dteInstances) {
    # Ensure DTE is ready
    $dte.MainWindow.Activate()
    
    # Attach to the target process
    try {
        $dte.Debugger.LocalProcesses | Where-Object { $_.ProcessID -eq $process.Id } | ForEach-Object {
            $_.Attach()
            Write-Output "Attached to process $ProcessName with PID $($process.Id)"
        }
    } catch {
        Write-Output "Failed to attach to process $ProcessName."
    }
}
