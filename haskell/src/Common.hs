module Common where

{-
takeWhileM <https://stackoverflow.com/questions/12119420/haskell-ghci-using-eof-character-on-stdin-with-getcontents>
-}

takeWhileM :: (Monad m, Functor m) => (a -> Bool) -> [m a] -> m [a]
takeWhileM p (ma : mas) = do
  a <- ma
  if p a
    then (a :) <$> takeWhileM p mas
    else return []
takeWhileM _ _ = return []

readInputContest :: IO [String]
readInputContest = lines <$> getContents

readInputsTerm :: IO [String]
readInputsTerm = takeWhileM (not . null) (repeat getLine)