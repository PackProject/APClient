# ============================================================================#
#                                                                             #
# Ninja build rule templates                                                  #
#                                                                             #
# ============================================================================#

from .config import KokeshiConfig
from .ninja_syntax import Writer
from .platform import chain_commands, gen_copy_cmd


def rule_install_tool(writer: Writer, config: KokeshiConfig):
    """Emits a Ninja build rule to install the specified tool

    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
    """

    writer.comment("Install tool")
    writer.rule(
        name="install_tool",
        command="$python $install_tool -t $name",
        description="TOOL ($name)",
    )
    writer.newline()


def rule_reconfigure(writer: Writer, config: KokeshiConfig):
    """Emits a Ninja build rule to re-run the configure script

    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
    """

    writer.comment("Re-run generator script")
    writer.rule(
        name="reconfigure",
        command="$python $configure",
        description="CONFIGURE",
        generator=True,
    )
    writer.newline()


def rule_checkrom(writer: Writer, config: KokeshiConfig):
    """Emits a Ninja build rule to check the base ROM integrity

    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
    """
    writer.comment("Check base ROM")
    writer.rule(
        name="checkrom",
        command="$python $checkrom --pack=$pack",
        description="CHECKROM ($pack)",
    )
    writer.newline()


def rule_compile(writer: Writer, config: KokeshiConfig):
    """Emits a Ninja build rule to compile the specified source file

    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
    """

    writer.comment("Compile source file")
    writer.rule(
        name="compile",
        command="$cc $cflags -MD -c $in -o $outdir",
        depfile="$depfile",
        deps="gcc",
        description="COMPILE $in",
    )
    writer.newline()


def rule_link(writer: Writer, config: KokeshiConfig):
    """Emits a Ninja build rule to link the specified executable

    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
    """

    writer.comment("Link binary")
    writer.rule(
        name="link",
        command="$ld $in $ldflags",
        description="LINK $name ($pack)",
    )
    writer.newline()


def rule_install_binary(writer: Writer, config: KokeshiConfig):
    """Emits a Ninja build rule to install the specified executable

    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
    """

    writer.comment("Install binary")
    writer.rule(
        name="install_binary",
        command=chain_commands([
            gen_copy_cmd("$bin_in", "$bin_out"),
            gen_copy_cmd("$map_in", "$map_out"),
        ]),
        description="INSTALL $name ($pack)",
        restat=True,
    )
    writer.newline()


def rule_install_asset(writer: Writer, config: KokeshiConfig):
    """Emits a Ninja build rule to install the specified asset file

    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
    """

    writer.comment("Install asset")
    writer.rule(
        name="install_asset",
        command=gen_copy_cmd("$in", "$out"),
        description="INSTALL $in ($pack)",
    )
    writer.newline()


def rule_clangd_commands(writer: Writer, config: KokeshiConfig):
    """Emits a Ninja build rule to create Clangd compilation commands
    Args:
        writer (Writer): Ninja writer
        config (KokeshiConfig): Project configuration
    """

    writer.comment("Create Clangd commands")
    writer.rule(
        name="clangd_commands",
        command="$python $make_compile_cmds",
        description="CLANGD",
    )
    writer.newline()
