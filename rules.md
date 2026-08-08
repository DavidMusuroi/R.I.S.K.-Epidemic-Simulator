# R.I.S.K. Simulator Rules & Mechanics

## 1. Compartment Model
Each region and country tracks four core population states based on an SIR-style epidemic model:
* **Susceptible (S)**: The uninfected population susceptible to contracting the disease.
* **Infected (I)**: Active cases capable of spreading the infection to neighbors.
* **Recovered (R)**: Individuals who have recovered and gained immunity.
* **Killed (K)**: Deceased individuals resulting from disease mortality.

---

## 2. Dynamic Population Calculations
During each update cycle, population transitions occur according to percentage-based updates:

* **Infection Calculation**: Converts `S * infection_rate / 100` people from Susceptible to Infected.
* **Recovery Calculation**: Converts `I * recovery_rate / 100` people from Recovered to Infected.
* **Mortality Calculation**: Converts `I * mortality_rate / 100` people from Infected to Killed.

---

## 3. Geographic & Environmental Modifiers
Regions have modifiers that dynamically adjust their infection rate (`i_rate`) and recovery rate (`r_rate`) multipliers upon initialization:

| Modifier | `i_rate` Multiplier | `r_rate` Multiplier | Effect Description |
| :--- | :--- | :--- | :--- |
| **`starting region`** | $1.5 \times$ | — | Applied exclusively to the initial outbreak location. |
| **`capital`** | $1.5 \times$ | $0.9 \times$ | High density accelerates transmission and hinders healthcare efficiency. |
| **`airport`** | $1.25 \times$ | $0.85 \times$ | High transit increases spread rate. |
| **`airfield`** | $1.20 \times$ | — | Regional travel increases infection spread. |
| **`port`** | $1.15 \times$ | $1.10 \times$ | Increased transmission with moderate recovery access. |
| **`river`** | $1.10 \times$ | $0.95 \times$ | Water channels slightly boost infection transmission. |
| **`dam`** | $1.05 \times$ | $1.05 \times$ | Minor increase to both transmission and recovery. |
| **`mine`** | $0.95 \times$ | $0.85 \times$ | Slightly lower transmission, reduced medical efficiency. |
| **`mountainous`** | $0.90 \times$ | $1.20 \times$ | Terrain isolation slows spread and aids recovery. |

---

## 4. Transmission & Daily Simulation Step (`next_day`)
When advancing the simulation step (`next_day`), the disease spreads across borders using neighbor links:

1. **Border Spread Calculation**: For every region with infected individuals (`I > 0`), a transmission buffer is accumulated for each adjacent neighbor:
   `Buffer Share = (i_rate * 0.02) / total_neighbors`
2. **Rate Adjustments**: For any neighboring region receiving a positive buffer:
   * Infection rate increases: `i_rate += buffer`
   * Recovery rate increases: `r_rate += buffer * 0.1`
   * Mortality rate increases: `m_rate += buffer * 0.05`
3. **Daily State Update (`update("end")`)**: All regions calculate new infection, recovery, and mortality population totals.