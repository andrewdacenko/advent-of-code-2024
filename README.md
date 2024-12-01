# advent-of-code-2024

# Prerequisite
Install buck2 https://buck2.build/docs/about/getting_started/

# Run
```
buck2 run //apps/<app>:<app> -- <args>
```

Example:
```
buck2 run //apps/historian_hysteria:historian_hysteria -- -i apps/historian_hysteria/input_1.txt
# or from `apps/historian_hysteria/`
buck2 run :historian_hysteria -- -i input_1.txt
```

