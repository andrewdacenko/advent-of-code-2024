# advent-of-code-2024

# Prerequisite
Install buck2 https://buck2.build/docs/about/getting_started/

# Run
```
buck2 run //apps/<app>:main -- <args>
```

Example:
```
buck2 run //apps/historian_hysteria:main -- -i apps/historian_hysteria/input.txt
# or from `apps/historian_hysteria/`
buck2 run :main -- -i input.txt
```

