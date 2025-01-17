import logging
import os
import shutil

from enum import Enum, auto
from typing import Sequence

from .targets import Target, ALL

ALL_TARGETS = ALL


class BuildSteps(Enum):
    GENERATED = auto()


class Context:
    """Represents a grouped list of platform/board/app builders to use

         to generate make/ninja instructions and to compile.
      """

    def __init__(self, runner, repository_path: str, output_prefix: str):
        self.builders = []
        self.runner = runner
        self.repository_path = repository_path
        self.output_prefix = output_prefix
        self.completed_steps = set()

    def SetupBuilders(self, targets: Sequence[Target], enable_flashbundle: bool):
        """Configures internal builders for the given platform/board/app combination. """

        self.builders = []
        for target in targets:
            self.builders.append(target.Create(
                self.runner, self.repository_path, self.output_prefix, enable_flashbundle))

        # whenever builders change, assume generation is required again
        self.completed_steps.discard(BuildSteps.GENERATED)

    def Generate(self):
        """Performs a build generation IFF code generation has not yet been performed."""
        if BuildSteps.GENERATED in self.completed_steps:
            return

        for builder in self.builders:
            logging.info('Generating %s', builder.output_dir)
            builder.generate()

        self.completed_steps.add(BuildSteps.GENERATED)

    def Build(self):
        self.Generate()

        for builder in self.builders:
            logging.info('Building %s', builder.output_dir)
            builder.build()

    def CleanOutputDirectories(self):
        for builder in self.builders:
            logging.warn('Cleaning %s', builder.output_dir)
            shutil.rmtree(builder.output_dir)

        # any generated output was cleaned
        self.completed_steps.discard(BuildSteps.GENERATED)

    def CreateArtifactArchives(self, directory: str):
        logging.info('Copying build artifacts to %s', directory)
        if not os.path.exists(directory):
            os.makedirs(directory)
        for builder in self.builders:
            # FIXME: builder subdir...
            builder.CompressArtifacts(os.path.join(
                directory, f'{builder.identifier}.tar.gz'))

    def CopyArtifactsTo(self, path: str):
        logging.info('Copying build artifacts to %s', path)
        if not os.path.exists(path):
            os.makedirs(path)

        for builder in self.builders:
            # FIXME: builder subdir...
            builder.CopyArtifacts(os.path.join(path, builder.identifier))
