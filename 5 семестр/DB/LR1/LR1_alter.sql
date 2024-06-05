--ИЗДАТЕЛЬСТВО
ALTER TABLE publishing_house
	ADD UNIQUE(website);

ALTER TABLE publishing_house
	ADD UNIQUE(phone);

--МАГАЗИН
ALTER TABLE shop
	ADD UNIQUE(website);

ALTER TABLE shop
	ADD CHECK(rating >= 0 and rating <= 10);

--ПРОИЗВЕДЕНИЕ
ALTER TABLE fiction
	ADD CHECK(year_wr >= 1 and year_wr <= 2022);
	