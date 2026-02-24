param(
    [string]$Root = "."
)

# Extensions to skip when editing file contents
$skip = @(".dll", ".exe", ".obj", ".bin", ".pdb")

function Replace-Name($text) {
    # Case‑sensitive replacements
    $text = $text -creplace 'geode', 'geode'
    $text = $text -creplace 'Geode', 'Geode'
    $text = $text -creplace 'GEODE', 'GEODE'
    return $text
}

Write-Host "=== Renaming folders ==="

# Rename directories deepest-first
Get-ChildItem -Path $Root -Recurse -Directory |
    Sort-Object FullName -Descending |
    ForEach-Object {
        # Skip modifying this script itself
        if ($_.FullName -like "*replace.ps1*") { return }

        $oldPath = $_.FullName
        $oldName = $_.Name
        $newName = Replace-Name $oldName

        if ($oldName -ne $newName) {
            Write-Host "Renamed folder: $oldPath -> $newName"
            Rename-Item -LiteralPath $oldPath -NewName $newName
        }
    }

Write-Host "=== Renaming files ==="

Get-ChildItem -Path $Root -Recurse -File | ForEach-Object {
    # Skip modifying this script itself