# hascripts

Copy package folder to config/packages/
Add the following to configuration.yaml

```
homeassistant:
  packages: !include_dir_named packages
```
scripts.yaml is obsolete

Blueprints can be imported using github URL's