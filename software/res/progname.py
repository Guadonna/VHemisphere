Import("env")
import subprocess

def revision():
    try:
        rev = subprocess.check_output(["git", "rev-parse", "--short", "HEAD"], stderr=subprocess.DEVNULL).decode().strip()
        if subprocess.check_output(["git", "status", "--porcelain", "--untracked-files=no"]).strip():
            rev += "-dirty"
        return rev
    except subprocess.CalledProcessError:
        return "uncommitted"

env.Append(CPPDEFINES=[("OC_BUILD_TAG", '\\"' + revision() + '\\"')])
env.Replace(PROGNAME="VHemisphere-v0.2.4-Teensy40")
