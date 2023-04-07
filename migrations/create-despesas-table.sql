CREATE TABLE despesas (
  id INT AUTO_INCREMENT PRIMARY KEY,
  usuario_id INT,
  descricao VARCHAR(255) NOT NULL,
  valor FLOAT NOT NULL,
  data_vencimento DATE NOT NULL,
  pago BOOLEAN NOT NULL,
  FOREIGN KEY (usuario_id) REFERENCES usuarios(id)
);