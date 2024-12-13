import shutil
import os

class BuildPackager:
    def __init__(self, build_dir, package_dir):
        self.build_dir = build_dir
        self.package_dir = package_dir

    def create_package(self):
        """Create a compressed archive of the build"""
        print(f"Creating package from {self.build_dir}...")
        shutil.make_archive(self.package_dir + "/game_build", 'zip', self.build_dir)
        print("Package created.")

    def deploy_package(self):
        """Deploy the package to a specific location"""
        package_file = self.package_dir + "/game_build.zip"
        deploy_path = "/path/to/deploy/dir"
        shutil.copy(package_file, deploy_path)
        print(f"Package deployed to {deploy_path}")

packager = BuildPackager("build_output", "package_output")
packager.create_package()
packager.deploy_package()