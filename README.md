# png2ico

This program uses [FreeImage](https://freeimage.sourceforge.io/) to combine multiple png's into an ico.

## Usage

It takes any number of positional arguments as png inputs. It also supports wildcards (but not ** globs). The `-o` argument optionally specifies a custom output file name.

```cmd
png2ico mylogo-*.png -o outlogo.ico
```

## Todo

It would be nice if this program could also take an svg and generate the common sized png's using [librsvg](https://wiki.gnome.org/action/show/Projects/LibRsvg?action=show&redirect=LibRsvg), therefore saving the need to export the png's from a tool like Illustrator or InkScape.
