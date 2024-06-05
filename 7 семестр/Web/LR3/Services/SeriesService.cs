using AutoMapper;
using Books.Repository;
using Books.Models;
using Books.ModelsBL;
using Books.Enums;

namespace Books.Services
{
	public interface ISeriesService
	{
		SeriesBL Add(SeriesBL user);
		SeriesBL Update(SeriesBL user);

		SeriesBL GetById(int id);
		SeriesBL GetByName(string name);

		IEnumerable<SeriesBL> GetByParameters(
			string? name, string? genre, string? publisher,
			int? year, int? rating,
			SearchFlag yearFlag, SearchFlag ratingFlag);
	}

	public class SeriesService : ISeriesService
	{
		private readonly ISeriesRepository _seriesRepository;
		private readonly IMapper _mapper;

		public SeriesService(ISeriesRepository seriesRepository,
							  IMapper mapper)
		{
			_seriesRepository = seriesRepository;
			_mapper = mapper;
		}


		private bool IsExist(SeriesBL series)
		{
			return _seriesRepository.GetAll().FirstOrDefault(elem =>
					elem.Name == series.Name) != null;
		}

		private bool IsNotExist(int id)
		{
			return _seriesRepository.GetById(id) == null;
		}

		public SeriesBL Add(SeriesBL series)
		{
			if (IsExist(series))
				throw new Exception("Такая серия уже существует");

			return _mapper.Map<SeriesBL>(_seriesRepository.Add(_mapper.Map<Series>(series)));

		}

		public SeriesBL Update(SeriesBL series)
		{
			if (IsNotExist(series.Id))
				throw new Exception("Такая серия не существует");

			return _mapper.Map<SeriesBL>(_seriesRepository.Update(_mapper.Map<Series>(series)));
		}

		public SeriesBL GetById(int id)
		{
			return _mapper.Map<SeriesBL>(_seriesRepository.GetById(id));
		}

		public SeriesBL GetByName(string name)
		{
			return _mapper.Map<SeriesBL>(_seriesRepository.GetByName(name));
		}

		public IEnumerable<SeriesBL> GetByParameters(
			string? name, string? genre, string? publisher,
			int? year, int? rating,
			SearchFlag yearFlag, SearchFlag ratingFlag)
		{
			var seriess = _seriesRepository.GetAll();

			if (seriess.Count() != 0 && name != null)
				seriess = seriess.Where(elem => elem.Name == name);

			if (seriess.Count() != 0 && genre != null)
				seriess = seriess.Where(elem => elem.Genre == genre);

			if (seriess.Count() != 0 && publisher != null)
				seriess = seriess.Where(elem => elem.Publisher == publisher);

			if (seriess.Count() != 0 && year != null)
			{
				if (yearFlag == SearchFlag.Equal)
					seriess = seriess.Where(elem => elem.Year == year);
				if (yearFlag == SearchFlag.More)
					seriess = seriess.Where(elem => elem.Year >= year);
				if (yearFlag == SearchFlag.Less)
					seriess = seriess.Where(elem => elem.Year <= year);
			}

			if (seriess.Count() != 0 && rating != null)
			{
				if (ratingFlag == SearchFlag.Equal)
					seriess = seriess.Where(elem => elem.Rating == rating);
				if (ratingFlag == SearchFlag.More)
					seriess = seriess.Where(elem => elem.Rating >= rating);
				if (ratingFlag == SearchFlag.Less)
					seriess = seriess.Where(elem => elem.Rating <= rating);
			}

			return _mapper.Map<IEnumerable<SeriesBL>>(seriess);

		}
	}
}
