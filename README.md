# Em

A small language for math operations.

## Sample working program

### Source

```
set := {1, 2, 3, 4}
set ⊆ ℝ
1 ∈ set
5 ∈ set
```

### Result (line by line)

```
{1, 3, 2, 4}
⊤
⊤
⊥
```

## Sets

### Operations

| Operation            | Syntax           | Return value | Supported |
|----------------------|------------------|--------------|-----------|
| Create material set  | `set := {1, 5}`  | Set          | ✅         |
| Create virtual set   | `set := {x ⊆ ℝ}` | Set          | ❌         |
| Union                | `{1, 2} ∪ {3}`   | Set          | ✅         |
| Intersection         | `{1, 2} ∩ {2}`   | Set          | ✅         |
| Difference           | `{1, 2} - {2}`   | Set          | ❌         |
| Symmetric difference | `{1, 2} ∆ {2}`   | Set          | ❌         |
| Cartesian product    | `{1} × {2}`      | Set          | ❌         | 
| Equality             | `{1} = {1}`      | Boolean      | ✅         |
| Not equality         | `{1, 3} ≠ {4}`   | Boolean      | ✅         |
| Element of           | `13 ∈ {1, 13}`   | Boolean      | ✅         |
| Not element of       | `17 ∉ {1, 13}`   | Boolean      | ❌         |
| Subset               | `{1} ⊆ {1, 2}`   | Boolean      | ✅         |
| Not subset           | `{3} ⊄ {1, 3}`   | Boolean      | ✅         |    
| Superset             | `{1, 2} ⊇ {1}`   | Boolean      | ❌         |
| Not superset         | `{3, 4} ⊅ {2}`   | Boolean      | ❌         |
| Strict subset        | `{1} ⊂ {1, 2}`   | Boolean      | ❌         | 
| Strict superset      | `{1, 7} ⊃ {7}`   | Boolean      | ❌         | 
| Cardinality          | `\|{1, 2, 3}\|`  | Number       | ❌         |

### Symbols

| Symbol           | Token | Value              |
|------------------|-------|--------------------|
| Empty set        | `∅`   | `{}`               |
| Real numbers set | `ℝ`   | `{x \| -∞ < x <∞}` |