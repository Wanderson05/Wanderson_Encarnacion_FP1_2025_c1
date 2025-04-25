
(
  SELECT
    'Inciso a' AS Inciso,
    p.C�digo,
    p.Producto,
    pr.Presentaci�n,
    NULL AS Contenido,
    p.Precio
  FROM Productos p
  JOIN Presentaciones pr ON p.C�digo = pr.C�digo
  WHERE p.Producto = 'Detergente' OR pr.Presentaci�n = 'Bolsa'
)

UNION ALL

(
  SELECT
    'Inciso b' AS Inciso,
    NULL AS C�digo,
    p.Producto,
    NULL AS Presentaci�n,
    pr.Contenido,
    p.Precio
  FROM Productos p
  JOIN Presentaciones pr ON p.C�digo = pr.C�digo
  WHERE p.Precio >= 15.00
     OR (pr.Contenido LIKE '%250%' OR pr.Contenido LIKE '%600%')
)

UNION ALL

(
  SELECT
    'Inciso c' AS Inciso,
    p.C�digo,
    p.Producto,
    pr.Presentaci�n,
    pr.Contenido,
    p.Precio
  FROM Productos p
  JOIN Presentaciones pr ON p.C�digo = pr.C�digo
  WHERE p.C�digo = 5513
)

UNION ALL

(
  SELECT
    'Inciso d' AS Inciso,
    p.C�digo,
    p.Producto,
    pr.Presentaci�n,
    NULL AS Contenido,
    NULL AS Precio
  FROM Productos p
  JOIN Presentaciones pr ON p.C�digo = pr.C�digo
  WHERE p.Producto = 'Detergente'
);
