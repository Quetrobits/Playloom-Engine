import os
import shutil
import subprocess

class BuildSystem:
    def __init__(self, project_dir, output_dir):
        self.project_dir = project_dir
        self.output_dir = output_dir

    def clean_build(self):
        """Clean previous builds"""
        if os.path.exists(self.output_dir):
            shutil.rmtree(self.output_dir)
        os.makedirs(self.output_dir)
        print(f"Cleaned previous builds. Output directory: {self.output_dir}")

    def compile_source(self):
        """Compile source code into executable"""
        print("Compiling source code...")
        # Example compilation command (replace with your own)
        subprocess.run(["g++", "-o", os.path.join(self.output_dir, "game_executable"), 
                        os.path.join(self.project_dir, "src/main.cpp")])
        print("Compilation complete.")

    def package_assets(self):
        """Package assets into the build"""
        print("Packaging assets...")
        assets_dir = os.path.join(self.project_dir, "assets")
        shutil.copytree(assets_dir, os.path.join(self.output_dir, "assets"))
        print("Assets packaged.")

    def run_tests(self):
        """Run tests on the build"""
        print("Running tests...")
        subprocess.run(["./tests/test_suite"])
        print("Tests complete.")

    def deploy(self):
        """Deploy the build to the specified location"""
        print(f"Deploying build to {self.output_dir}...")
        # Example deploy (copying the build to a deployment folder)
        deploy_dir = os.path.join(self.project_dir, "deploy")
        shutil.copytree(self.output_dir, deploy_dir)
        print(f"Deployment complete. Files located in {deploy_dir}")

    def build(self):
        """Full build process"""
        self.clean_build()
        self.compile_source()
        self.package_assets()
        self.run_tests()
        self.deploy()
        
build_system = BuildSystem("path_to_your_project", "path_to_output")
build_system.build()