
(
  SELECT
    'Inciso a' AS Inciso,
    p.Código,
    p.Producto,
    pr.Presentación,
    NULL AS Contenido,
    p.Precio
  FROM Productos p
  JOIN Presentaciones pr ON p.Código = pr.Código
  WHERE p.Producto = 'Detergente' OR pr.Presentación = 'Bolsa'
)

UNION ALL

(
  SELECT
    'Inciso b' AS Inciso,
    NULL AS Código,
    p.Producto,
    NULL AS Presentación,
    pr.Contenido,
    p.Precio
  FROM Productos p
  JOIN Presentaciones pr ON p.Código = pr.Código
  WHERE p.Precio >= 15.00
     OR (pr.Contenido LIKE '%250%' OR pr.Contenido LIKE '%600%')
)

UNION ALL

(
  SELECT
    'Inciso c' AS Inciso,
    p.Código,
    p.Producto,
    pr.Presentación,
    pr.Contenido,
    p.Precio
  FROM Productos p
  JOIN Presentaciones pr ON p.Código = pr.Código
  WHERE p.Código = 5513
)

UNION ALL

(
  SELECT
    'Inciso d' AS Inciso,
    p.Código,
    p.Producto,
    pr.Presentación,
    NULL AS Contenido,
    NULL AS Precio
  FROM Productos p
  JOIN Presentaciones pr ON p.Código = pr.Código
  WHERE p.Producto = 'Detergente'
);
